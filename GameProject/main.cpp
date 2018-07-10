//
//  main.cpp
//  GameProject
//
//  Created by Zhenhua Cai on 7/4/18.
//  Copyright © 2018 Zhenhua Cai. All rights reserved.
//

#include <iostream>
#include "pong.hpp"
int main(int argc, const char * argv[]) {
    using namespace std;
    
    Pong p;
    bool sucess=p.init();
    if(sucess){
        p.runLoop();
    }
    p.exit();
    return 0;
}
