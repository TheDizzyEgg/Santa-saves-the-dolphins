#include "_Shader.h"



_ShaderSystem::_ShaderSystem()
{
}

_ShaderSystem::~_ShaderSystem()
{
    al_use_shader(NULL);

    if(shaderLights != NULL)
    {
        al_destroy_shader(shaderLights);
    }

    if(shaderClear != NULL)
    {
        al_destroy_shader(shaderClear);
    }

    writeLog("Shader system cleaned successfully", 0);
}


void _ShaderSystem::createShaders()
{
    shaderLights = al_create_shader(ALLEGRO_SHADER_GLSL);
    shaderClear = al_create_shader(ALLEGRO_SHADER_GLSL);

    if(!shaderLights || !shaderClear)
    {
        writeLog("Error creating GLSL shaders...", 122);
    }

   if (!al_attach_shader_source_file(shaderLights, ALLEGRO_VERTEX_SHADER, "shader_vertex.glsl")) {
        writeLog("Error attaching shaderLights (/shader_vertex.glsl...)", 123);
   }

   if (!al_attach_shader_source_file(shaderClear, ALLEGRO_VERTEX_SHADER, "shader_vertex.glsl")) {
        writeLog("Error attaching shaderClear (/shader_vertex.glsl...)...", 123);
   }

   if (!al_attach_shader_source_file(shaderLights, ALLEGRO_PIXEL_SHADER, "shader_lights.glsl")) {
        writeLog("Error attaching shaderLights (/shader_lights.glsl...)", 123);
   }

   if (!al_attach_shader_source_file(shaderClear, ALLEGRO_PIXEL_SHADER, "shader_clear.glsl")) {
        writeLog("Error attaching shaderClear (/shader_clear.glsl...)...", 123);
   }

   if(!al_build_shader(shaderLights)){
       writeLog("Error building shaderLights...", 124);
   }

   if(!al_build_shader(shaderClear)){
       writeLog("Error building shaderClear...", 124);
   }

   for(int i = 0; i < 32; i++)
   {
       sprintf(stringLightAlive[i], "lightAlive[%i]", i);
       sprintf(stringLightX[i], "lightX[%i]", i);
       sprintf(stringLightY[i], "lightY[%i]", i);
       sprintf(stringLightDiffuse[i], "lightDiffuse[%i]", i);
       sprintf(stringLightPower[i], "lightPower[%i]", i);
   }
}

void _ShaderSystem::useShader(int shaderType)
{
    if(shaderType == SHADER_TYPE_LIGHT)
    {
        al_use_shader(shaderLights);
    }
    else if(shaderType == SHADER_TYPE_CLEAR)
    {
        al_use_shader(shaderClear);
    }
}


void _ShaderSystem::enableLight(int lightIndex)
{
    al_set_shader_bool(stringLightAlive[lightIndex], true);
}

void _ShaderSystem::disableLight(int lightIndex)
{
    al_set_shader_bool(stringLightAlive[lightIndex], false);
}

void _ShaderSystem::updateLight(int lightIndex, float lightX, float lightY, float lightPower, float lightRed, float lightGreen, float lightBlue)
{
    al_use_shader(shaderLights);

    al_set_shader_float(stringLightX[lightIndex], lightX);
    al_set_shader_float(stringLightY[lightIndex], lightY);
    al_set_shader_float(stringLightPower[lightIndex], lightPower);

    diffuseColor[0][0] = lightRed;
    diffuseColor[0][1] = lightGreen;
    diffuseColor[0][2] = lightBlue;

    al_set_shader_float_vector(stringLightDiffuse[lightIndex], 3, (float*)diffuseColor, 1);

    al_use_shader(NULL);
}

void _ShaderSystem::updateClear(float clearValue)
{
    al_use_shader(shaderClear);

    al_set_shader_float("tint", clearValue);

    al_use_shader(NULL);
}

void _ShaderSystem::updateLightPositions(_Map *mapActive, _PenguinSystem *penguinSystemActive)
{
    al_use_shader(shaderLights);

    for(int i=1; i<20; i++)
    {
        al_set_shader_float(stringLightX[i], lightX[i] - mapActive->x);
        al_set_shader_float(stringLightY[i], lightY[i] - mapActive->y);
    }

    for(int i=20; i<(int)penguinSystemActive->penguin.size() + 20 ; i++)
    {
        al_set_shader_float(stringLightX[i], penguinSystemActive->penguin[i - 20]->x + 20 - mapActive->x);
        al_set_shader_float(stringLightY[i], penguinSystemActive->penguin[i - 20]->y + 45 - mapActive->y);
    }

    stopShaders();
}



void _ShaderSystem::createMapLights(_Map *mapActive)
{
    int lightIndex = 1;

    al_use_shader(shaderLights);

    for(int yy = 0; yy < 40; yy++)
    {
        for(int xx = 0; xx < 80; xx++)
        {
            if(mapActive->boundsData[yy][xx] >> 8 == 105)
            {
                diffuseColor[0][0] = 1.0;
                diffuseColor[0][1] = 1.0;
                diffuseColor[0][2] = 0.9;

                al_set_shader_bool(stringLightAlive[lightIndex], true);
                al_set_shader_float(stringLightX[lightIndex], xx * 32 + 20);
                al_set_shader_float(stringLightY[lightIndex], yy * 32 + 20);
                al_set_shader_float_vector(stringLightDiffuse[lightIndex], 3, (float*)diffuseColor, 1);
                al_set_shader_float(stringLightPower[lightIndex], 150.0);

                lightX[lightIndex] =  xx * 32 + 20;
                lightY[lightIndex] =  yy * 32 + 20;
                lightIndex++;
            }
            else if(mapActive->boundsData[yy][xx] >> 8 == 106)
            {
                diffuseColor[0][0] = 1.0;
                diffuseColor[0][1] = 0.3;
                diffuseColor[0][2] = 0.3;

                al_set_shader_bool(stringLightAlive[lightIndex], true);
                al_set_shader_float(stringLightX[lightIndex], xx * 32 + 20);
                al_set_shader_float(stringLightY[lightIndex], yy * 32 + 20);
                al_set_shader_float_vector(stringLightDiffuse[lightIndex], 3, (float*)diffuseColor, 1);
                al_set_shader_float(stringLightPower[lightIndex], 150.0);

                lightX[lightIndex] =  xx * 32 + 20;
                lightY[lightIndex] =  yy * 32 + 20;
                lightIndex++;
            }
        }
    }
}

void _ShaderSystem::updateDaylight(int currentSnowflakes)
{
    al_use_shader(shaderLights);

    al_set_shader_float("daylight", 3.0 - ((currentSnowflakes * 3.0) / TOTAL_SNOWFLAKES));

    al_use_shader(NULL);
}


void _ShaderSystem::stopShaders()
{
    al_use_shader(NULL);
}

void _ShaderSystem::createPenguinLights(_PenguinSystem *penguinSystemActive)
{
    al_use_shader(shaderLights);

    diffuseColor[0][0] = 1.0;
    diffuseColor[0][1] = 1.0;
    diffuseColor[0][2] = 1.0;

    for(int i=0; i<(int)penguinSystemActive->penguin.size(); i++)
    {
        al_set_shader_float(penguinSystemActive->penguin[i]->stringLightX, penguinSystemActive->penguin[i]->x + 25);
        al_set_shader_float(penguinSystemActive->penguin[i]->stringLightY, penguinSystemActive->penguin[i]->y + 55);
        al_set_shader_float(penguinSystemActive->penguin[i]->stringLightPower, 130);
        al_set_shader_float_vector(penguinSystemActive->penguin[i]->stringLightDiffuse, 3, (float*)diffuseColor, 1);
        al_set_shader_bool(penguinSystemActive->penguin[i]->stringLightAlive, true);
    }

    al_use_shader(NULL);
}
