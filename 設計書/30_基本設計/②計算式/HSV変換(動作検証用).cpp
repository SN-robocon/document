//3.色取得 RGB値
getRGB(RGB);
printf("R:%f ,G:%f ,B:%f\n",RGB.r,RGB.g,RGB.b);

double red,green,blue;
red = RGB.r;
green = RGB.g;
blue = RGB.b;

double max_rgb = max((max(red,green)),blue);
double min_rgb = min((min(red,green)),blue);
value = max_rgb/256*100;

if(max_rgb==min_rgb){
    hue = 0;
    saturation = 0;
}else{
    if(max_rgb == red){
        hue = 60.0*(green-blue)/(max_rgb-min_rgb) + 0;
    }else if(max_rgb == green) {
        hue = 60.0*(blue-red)/(max_rgb-min_rgb) + 120.0;
    }else if(max_rgb == blue){
        hue = 60.0*(red-green)/(max_rgb-min_rgb) + 240.0;
    }

    if(hue > 360.0) {
        hue = hue - 360.0;
    }else if(hue < 0){
        hue = hue + 360.0;
    }
    
    saturation = (max_rgb-min_rgb)/max_rgb*100.0;
}
printf("H:%f ,S:%f ,V:%f\n",hue,saturation,value);

double diff_h = abs(hue - hsv.h);
double diff_s = abs(saturation - hsv.s);
double diff_v = abs(value - hsv.v);

printf("diff_h:%f ,diff_s:%f ,diff_v:%f\n",diff_h,diff_s,diff_v);