//
//  shooter.cpp
//  snoodyCandyPhotoSaga
//
//  Created by Clay Ewing on 1/24/14.
//
//

#include "shooter.h"
#define RED     ofColor(255,0,0)
#define GREEN   ofColor(0,255,0)
#define BLUE    ofColor(0,0,255)

void Shooter::display() {
    ofSetColor(255, 255, 255);
    candyImages[bullets[1].type].draw(position.x-10, position.y + 60, bullet_width/2, bullet_width/2);
    for (int i = 0; i < bullets.size(); i++) {
        bullets[i].display();
    }

    staff.draw(position.x - 15, position.y, 80, 136);
    if (bullets.size() > 0) {
        if (!bulletBeingShot) {
            candyImages[bullets[0].type].draw(position.x, position.y + 10, bullet_width, bullet_width);
        }
        

        ofSetColor(255, 255, 255);
    }
}
void Shooter::create(float x, float y, int w, vector<int> b_types) {
    bullets.clear();
    bullet_width = w;
    bulletBeingShot = false;
    position.set(x, y);
    candyImages[RED_TYPE].loadImage("red4.png");
    candyImages[GREEN_TYPE].loadImage("green4.png");
    candyImages[BLUE_TYPE].loadImage("blue4.png");
    staff.loadImage("staff.png");
    for (int x = 0; x < ofGetWidth(); x+=w) {
        crates.push_back(ofPoint(x, y));
    }
    
    int centerCrate = crates.size() / 2;
    position.set(crates[centerCrate].x, y);
    for (int i = 0; i < b_types.size(); i++) {
        Bullet tmpBullet;
        tmpBullet.create(w, w, b_types[i], &candyImages[b_types[i]]);
        bullets.push_back(tmpBullet);
    }

}
void Shooter::move(float x, float y) {
    float closestCrateDistance = 999999;
    int closestCrate = -1;
    for (int i = 0; i < crates.size(); i++) {
        float distanceToCrate = ofDist(x, y, crates[i].x, crates[i].y);
        if (distanceToCrate < closestCrateDistance) {
            closestCrate = i;
            closestCrateDistance = distanceToCrate;
        }
    }
    position.set(crates[closestCrate].x, crates[closestCrate].y);
}

void Shooter::reload() {
        Bullet tmpBullet;
        int colorSelect = ofRandom(0,3);
        tmpBullet.create(bullet_width, bullet_width, colorSelect, &candyImages[colorSelect]);
        bullets.push_back(tmpBullet);
    
}

void Shooter::shoot() {
    bullets[0].shoot(position);
    bulletBeingShot = true;
//    reload();
}
