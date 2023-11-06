Color::Color(){}

Color::Color(int r, int g, int b, int a){
            red = r;
            green = g;
            blue = b;
            alpha = a;
        }

double Color::calculateSaturation() const {    
            double r = red / 255.0;
            double g = green / 255.0;
            double b = blue / 255.0;
            double maxValue = std::max({r, g, b});
            double minValue = std::min({r, g, b});
            double diff = maxValue - minValue;
            double ligthness = (maxValue + minValue) / 2.0;
            if (diff == 0) {
                return 0;
            } else {
                double saturation = diff / (1 - fabs(2 * ligthness - 1));
                return saturation;
            }

}