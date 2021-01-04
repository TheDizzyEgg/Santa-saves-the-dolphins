
#include "_System.h"



_System::_System()
{
    running = false;
    redraw = true;
    fadeAmount = 0.0;
}

_System::~_System()
{
    if(display != NULL)
    {
        al_destroy_display(display);
    }

    if(event_queue != NULL)
    {
        al_destroy_event_queue(event_queue);
    }

    if(timer != NULL)
    {
        al_destroy_timer(timer);
    }

    if(imgBuffer != NULL)
    {
        al_destroy_bitmap(imgBuffer);
    }

    if(imgBuffer2 != NULL)
    {
        al_destroy_bitmap(imgBuffer2);
    }

    if(imgIntro != NULL)
    {
        al_destroy_bitmap(imgIntro);
    }

    writeLog("System cleaned successfully", 0);
}


void _System::initialise()
{
	if (!al_init() || !al_init_image_addon() || !al_install_keyboard()) {
		writeLog("Failed to initialize allegro...", 91);
	}


    al_set_new_display_refresh_rate(60);
    al_set_new_display_flags(ALLEGRO_WINDOWED | ALLEGRO_PROGRAMMABLE_PIPELINE | ALLEGRO_OPENGL);

    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_REQUIRE);
    al_set_new_display_option(ALLEGRO_SAMPLES, 16, ALLEGRO_REQUIRE);
    al_set_new_display_option(ALLEGRO_RENDER_METHOD, 1, ALLEGRO_REQUIRE);
    al_set_new_display_option(ALLEGRO_VSYNC, 1, ALLEGRO_REQUIRE);
    al_set_new_display_option(ALLEGRO_SUPPORT_NPOT_BITMAP, 1, ALLEGRO_REQUIRE);


	display = al_create_display(1280, 720);
	if (!display) {
		writeLog("Failed to create display...", 92);
	}

	al_hide_mouse_cursor(display);

    al_set_new_bitmap_flags(ALLEGRO_VIDEO_BITMAP | ALLEGRO_NO_PRESERVE_TEXTURE | ALLEGRO_CONVERT_BITMAP);

	timer = al_create_timer(((1.0 / 60.0)) + 0.0001);
	if (!timer) {
		writeLog("Failed to create timer...", 93);
	}

	event_queue = al_create_event_queue();
	if (!event_queue) {
		writeLog("Failed to create event queue...", 94);
	}


    al_uninstall_mouse();

	al_register_event_source(event_queue, al_get_timer_event_source(timer));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_display_event_source(display));

	al_init_primitives_addon();


    al_init_font_addon();
    al_init_ttf_addon();

    fontMain = al_load_ttf_font("gfx/manaspc.ttf", 30, ALLEGRO_TTF_MONOCHROME);

    if(!fontMain)
    {
        writeLog("Unable to load ttf font: gfx/manaspc.ttf", 921);
    }

    fontSmall = al_load_ttf_font("gfx/manaspc.ttf", 24, ALLEGRO_TTF_MONOCHROME);

    if(!fontSmall)
    {
        writeLog("Unable to load ttf font: gfx/manaspc.ttf", 921);
    }

    fontLarge = al_load_ttf_font("gfx/manaspc.ttf", 34, ALLEGRO_TTF_MONOCHROME);

    if(!fontLarge)
    {
        writeLog("Unable to load ttf font: gfx/manaspc.ttf", 921);
    }

    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);

    imgBuffer = al_create_bitmap(1280, 720);

    if(imgBuffer == NULL)
    {
        writeLog("Could not create _System::imgBuffer", 143);
    }

    imgBuffer2 = al_create_bitmap(1280, 720);

    if(imgBuffer2 == NULL)
    {
        writeLog("Could not create _System::imgBuffer2", 143);
    }

    al_set_target_bitmap(imgBuffer2);
    al_clear_to_color(al_map_rgb(0, 0, 0));

    colorBlack = al_map_rgb(0, 0, 0);

}

void _System::useBuffer()
{
    al_set_target_bitmap(imgBuffer);
}

void _System::useBuffer2()
{
    al_set_target_bitmap(imgBuffer2);
}

void _System::useDisplay()
{
    al_set_target_bitmap(al_get_backbuffer(display));
}

void _System::renderBuffer()
{
    al_draw_bitmap(imgBuffer, 0, 0, 0);
}

void _System::renderBuffer2()
{
    al_draw_bitmap(imgBuffer2, 0, 0, 0);
}


void _System::printText(ALLEGRO_FONT *fontActive, ALLEGRO_COLOR colorActive, float x, float y, float flags, const char *textData)
{
    al_draw_text(fontActive, colorBlack, x, y + 2, flags, textData);
    al_draw_text(fontActive, colorActive, x, y, flags, textData);
}

void _System::renderFade()
{
    al_draw_tinted_bitmap(imgBuffer2, al_map_rgba_f(1.0, 1.0, 1.0, fadeAmount), 0, 0, 0);
}

void _System::loadIntroBitmap()
{
    if(imgIntro != NULL) al_destroy_bitmap(imgIntro);

    imgIntro = NULL;

    imgIntro = al_load_bitmap("gfx/title.png");

    if(!imgIntro)
    {
        writeLog("Error loading gfx/title.png", 1011);
    }
}


