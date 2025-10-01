#include <opencv2/opencv.hpp>
#include <iostream>
#include <fstream>
#include <string>

enum class DetectionState {
    NONE,
    RED,
    BLUE,
    GATE
};

std::string stateToString(DetectionState state) {
    switch (state) {
        case DetectionState::RED:  return "赤";
        case DetectionState::BLUE: return "青";
        case DetectionState::GATE: return "ゲート";
        default:                   return "何もない";
    }
}

int main() {
    DetectionState prevState    = DetectionState::NONE;
    DetectionState currentState = DetectionState::NONE;

    // カメラを開く
    cv::VideoCapture cap(0);
    if (!cap.isOpened()) {
        std::cerr << "カメラが開けませんでした。" << std::endl;
        return -1;
    }

    // ログファイルを開く
    std::ofstream logFile("log.txt");
    if (!logFile.is_open()) {
        std::cerr << "ログファイルを開けませんでした。" << std::endl;
        return -1;
    }

    // ゲートのテンプレート画像を読み込む
    cv::Mat gateTemplate = cv::imread("gate.jpg");
    if (gateTemplate.empty()) {
        std::cerr << "ゲート画像が読み込めませんでした。" << std::endl;
        return -1;
    }

    // カメラの設定
    cap.set(cv::CAP_PROP_FPS, 10);
    cap.set(cv::CAP_PROP_FRAME_WIDTH, 640);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480);

    // メインループ
    cv::Mat frame;
    while (true) {
        cap >> frame;
        if (frame.empty()) break;

        // RGB形式のカメラ画像(frame)をHSV形式に変換を行い、hsvに保存する処理
        cv::Mat hsv;
        cv::cvtColor(frame, hsv, cv::COLOR_BGR2HSV);

        // 赤色マスクの作成（HSV範囲）
        cv::Mat lower_red_mask, upper_red_mask, red_mask;
        cv::inRange(hsv, cv::Scalar(0, 70, 50), cv::Scalar(10, 255, 255), lower_red_mask);
        cv::inRange(hsv, cv::Scalar(170, 70, 50), cv::Scalar(180, 255, 255), upper_red_mask);
        cv::bitwise_or(lower_red_mask, upper_red_mask, red_mask);

        // 青色マスクの作成
        cv::Mat blue_mask;
        cv::inRange(hsv, cv::Scalar(100, 150, 0), cv::Scalar(130, 255, 255), blue_mask);

        // 検出割合の計算
        double red_ratio = cv::sum(red_mask)[0] / (red_mask.total() * 255.0);
        double blue_ratio = cv::sum(blue_mask)[0] / (blue_mask.total() * 255.0);
        
        std::cout << std::fixed << std::setprecision(2);
        std::cout << "赤：" << red_ratio * 100.0 << "%,青：" << blue_ratio * 100.0 << "%" << std::endl;

        // 状態の初期化
        currentState = DetectionState::NONE;

        // 赤 or 青の状態判定
        if (red_ratio >= 0.03) {
            currentState = DetectionState::RED;
        } 
        if (blue_ratio >= 0.03) {
            currentState = DetectionState::BLUE;
        }
        bool gateDetected = false;  // ← ゲート検出フラグを追加

        // テンプレート画像がフレームより小さい場合のみ処理する
        if (gateTemplate.cols <= frame.cols && gateTemplate.rows <= frame.rows) {
            int result_cols = frame.cols - gateTemplate.cols + 1;
            int result_rows = frame.rows - gateTemplate.rows + 1;

            if (result_cols > 0 && result_rows > 0) {
                cv::Mat result(result_rows, result_cols, CV_32FC1);
                cv::matchTemplate(frame, gateTemplate, result, cv::TM_CCOEFF_NORMED);

                double minVal, maxVal;
                cv::Point minLoc, maxLoc;
                cv::minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc);

                if (maxVal > 0.5) {
                    gateDetected = true;  // ← ゲートを検出したと記録

                    // 枠を描画
                    cv::rectangle(frame, maxLoc,
                        cv::Point(maxLoc.x + gateTemplate.cols, maxLoc.y + gateTemplate.rows),
                        cv::Scalar(0, 255, 0), 3);
                }
            }
        }

        // ゲートが検出された場合の処理
        if (gateDetected) {
            if (currentState != DetectionState::GATE) {
                currentState = DetectionState::GATE;
            }
        }


        // 状態変化時にログと出力
        if (currentState != prevState) {
            std::string msg = stateToString(currentState);
            std::cout << "状態変化: " << msg << std::endl;
            logFile << msg << std::endl;
            logFile.flush();
            prevState = currentState;
        }

        cv::imshow("Webcam", frame);
        if (cv::waitKey(1) == 'q') break;
    }

    cap.release();
    logFile.close();
    cv::destroyAllWindows();
    return 0;
}
