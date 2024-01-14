#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>

typedef struct
{
    int x;
    int y;
} point;

int main()
{

    int centre_x = 900;
    int centre_y = 500;
    int i;
    MLV_Image *img_point;
    MLV_create_window("Angle", "Angle", 1000, 1000);
    MLV_clear_window(MLV_COLOR_WHITE);
    img_point = MLV_load_image("point.png");
    MLV_resize_image_with_proportions(img_point, 20, 20);

    for (i = 1; i <= 20; i++)
    {
        MLV_draw_line(i * 40, 20, i * 40, 820, MLV_COLOR_BLACK);
        MLV_draw_line(20, i * 40, 820, 40 * i, MLV_COLOR_BLACK);
    }
    MLV_draw_line(50,900, 950,900, MLV_COLOR_RED);
    MLV_draw_image(img_point, centre_y - 10, centre_x);

    point initial;
    MLV_actualise_window();
        MLV_wait_mouse(&initial.y , &initial.x);
    
    //initial.x = 50;
    //initial.y = 50;
    float coef_a;
    float coef_b;
    coef_a = (((float)centre_y - (float)initial.y) / ((float)centre_x - (float)initial.x));
    printf(" %f\n", coef_a);
    coef_b = initial.y - coef_a * initial.x;

    printf("Le coef est : y = %f x + %f\n", coef_a, coef_b);


    // CAlcul des points d'intersection :
    int retour = 0;

    for (i = 0; i < 500; i++)
    {
        if (retour)
        {
            initial.x -= 10;
            initial.y = coef_a * initial.x + coef_b;
        }
        else
        {
            initial.x += 10;
            initial.y = coef_a * initial.x + coef_b;
        }

        MLV_draw_image(img_point, initial.y - 10, initial.x);
        MLV_actualise_window();
        MLV_wait_milliseconds(100);
        if (initial.x > centre_x && !retour) 
        {
            retour = 1;
            coef_a = -coef_a; // pente
            coef_b = initial.y - coef_a * initial.x; // ordonnée origine
        }
    }

    MLV_wait_seconds(5);

    MLV_actualise_window();
    MLV_wait_seconds(5);
}