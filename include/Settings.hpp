#ifndef SETTINGS_HPP
#define SETTINGS_HPP

namespace bd{

    class Settings {
        int nbBoids;
        int widthWindow;
        int heightWindow;
        /**
         * Max speed of a Boid
         */
        float vmax;
        /**
         * limitSpeed of a Boid
         */
        float amax;
        /**
         * Ray of perception of Boids
         */
        float pixelR;
        /**
         * Distance between Boids
         */
        float distMin;
        /**
         * weight of Cohesion rule
         */
        float wC;
        /**
         * weight of Alignment rule
         */
        float wA;
        /**
         * weight of Separation rule
         */
        float wS;

        template <typename T>
        T clamp(const T&, const T&, const T&);

        public:
        Settings();

        int getNbBoids() const;
        int getWidthWindow() const;
        int getHeightWindow() const;

        float getVMax() const;
        float getAMax() const;

        float getPixelR() const;
        float getDistMin() const;

        float getWC() const;
        float getWA() const;
        float getWS() const;

        void setNbBoids(const int&);
        void setPixelR(const float&);
        void setDistMin(const float&);

        void setWC(const float&);
        void setWA(const float&);
        void setWS(const float&);
    };

    template <typename T>
    T Settings::clamp(const T& val, const T& min, const T& max){
        if(min > val) {
            return min;
        } else if (max < val){
            return max;
        } else {
            return val;
        }
    }
}

#endif