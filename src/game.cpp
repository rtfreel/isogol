#include "game.h"
#include "globals.h"

#include <GL/gl.h> 
#include <GL/glu.h>


Game::Game(char *name, int width, int height) : _name(name), _width(width), _height(height) {
	init();
	initGL();
}

Game::~Game() { close(); }

void Game::start(){
	_running = true;
    setup();
	SDL_StartTextInput();

	while( _running ){
        //event handling
		SDL_Event event;
		while( SDL_PollEvent( &event ) != 0 ) {
			if( event.type == SDL_QUIT ) {
				_running = false;
			} else if( event.type == SDL_TEXTINPUT ) {
				int x = 0, y = 0;
				SDL_GetMouseState( &x, &y );
				handleKeys( event.text.text[ 0 ], x, y );
			}
		}

        //apply and draw all changes
		update();
		render();
		
		SDL_GL_SwapWindow( _window );
	}
	SDL_StopTextInput();
}

bool Game::init(){
    bool success = true;

    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    } else {
        //Use OpenGL 3.1
        SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, global::MAGOR_V );
        SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, global::MINOR_V );

        _window = SDL_CreateWindow( _name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, _width, _height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );
        if( _window == NULL ) {
            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
        } else {
            //Create context
            glContext = SDL_GL_CreateContext( _window );
            if( glContext == NULL ) {
                printf( "OpenGL context could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            } else {
                //Use Vsync
                if( SDL_GL_SetSwapInterval( 1 ) < 0 ) {
                    printf( "Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError() );
                }

                //Initialize OpenGL
                if( !initGL() ) {
                    printf( "Unable to initialize OpenGL!\n" );
                    success = false;
                }
            }
        }
    }
    return success;
}

bool Game::initGL(){
	bool success = true;
    GLenum error = GL_NO_ERROR;

    //Initialize Projection Matrix
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    
    //Check for error
    error = glGetError();
    if( error != GL_NO_ERROR ) {
        printf( "Error initializing OpenGL! %s\n", gluErrorString( error ) );
        success = false;
    }

    //Initialize Modelview Matrix
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    //Check for error
    error = glGetError();
    if( error != GL_NO_ERROR ) {
        printf( "Error initializing OpenGL! %s\n", gluErrorString( error ) );
        success = false;
    }
	//Initialize clear color
    glClearColor( 0.f, 0.f, 0.f, 1.f );
    gluOrtho2D(0, _width, 0, _height);
    
    //Check for error
    error = glGetError();
    if( error != GL_NO_ERROR ) {
        printf( "Error initializing OpenGL! %s\n", gluErrorString( error ) );
        success = false;
    }
    
    return success;
}

void Game::close() {}

int Game::getWidth() { return _width; }
int Game::getHeight() { return _height; }


