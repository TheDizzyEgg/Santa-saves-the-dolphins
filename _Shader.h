#ifndef _SHADER_H
#define _SHADER_H

#include "_Decls.h"

#define SHADER_TYPE_LIGHT 1
#define SHADER_TYPE_CLEAR 2

class _ShaderSystem;

class _ShaderSystem
{
    public:
        _ShaderSystem();
        virtual ~_ShaderSystem();

        ALLEGRO_SHADER* shaderLights;
        ALLEGRO_SHADER* shaderClear;

        float diffuseColor[1][3];

        char stringLightAlive[32][255];
        char stringLightX[32][255];
        char stringLightY[32][255];
        char stringLightDiffuse[32][255];
        char stringLightPower[32][255];
        float lightX[32];
        float lightY[32];

        void createShaders();
        void createMapLights(_Map *mapActive);
        void createPenguinLights(_PenguinSystem *penguinSystemActive);
        void useShader(int shaderType);
        void stopShaders();
        void enableLight(int lightIndex);
        void disableLight(int lightIndex);
        void updateLight(int lightIndex, float lightX, float lightY, float lightPower, float lightRed, float lightGreen, float lightBlue);
        void updateClear(float clearValue);
        void updateDaylight(int currentSnowflakes);
        void updateLightPositions(_Map *mapActive, _PenguinSystem *penguinSystemActive);

};

#endif // _SHADER_H
