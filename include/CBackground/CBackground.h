#ifndef CBACKGROUND_H
#define CBACKGROUND_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <CConfig.h>

class CBackground : public sf::Drawable
{
    public:
        CBackground();
        virtual ~CBackground();
        float calculateStarSpeed();
        void updateStars();
        sf::IntRect calculateStarRect(unsigned int Star);
        void setStarSpeed(float minSpeed, float maxSpeed);
    protected:
        std::vector<sf::IntRect> starRectangles;
        std::vector<float> starSpeed;
        std::vector<sf::Sprite*> Stars;
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
        float starMinSpeed;
        float starMaxSpeed;
        int WindowX, WindowY;
    private:
        bool firstRun; //This initializes the background directly in the view
};

#endif // CBACKGROUND_H
