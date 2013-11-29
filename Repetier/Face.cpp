
#include "Face.h"

uint8_t Face::current_id = 0;

Face::Face()
{ 
    id = current_id;
    h = LVM_DEFAULT_H;
    v = LVM_DEFAULT_V;
    color.r = LVM_DEFAULT_COLOR;
    color.g = LVM_DEFAULT_COLOR;
    color.b = LVM_DEFAULT_COLOR;
    color.i = LVM_DEFAULT_COLOR;
    
    ++current_id;
}

void Face::set_color( Color &c )
{
    color = c;
}

Color Face::get_color()
{
    return color;
}

uint8_t Face::get_h_intensity()
{
    return h;
}

uint8_t Face::get_v_intensity()
{
    return v;
}   
    
void Face::set_intensity( uint8_t nh, uint8_t nv) 
{
    h = nh;
    v = nv;
    switch ( id )
    {
        case 0:
            WRITE_VPIN( SELECT_DEFINE_FACE( 0, V ), nv );
            WRITE_VPIN( SELECT_DEFINE_FACE( 0, H ), nh );
        break;
        case 1:
            WRITE_VPIN( SELECT_DEFINE_FACE( 1, V ), nv );
            WRITE_VPIN( SELECT_DEFINE_FACE( 1, H ), nh );
        break;
        case 2:
            WRITE_VPIN( SELECT_DEFINE_FACE( 2, V ), nv );
            WRITE_VPIN( SELECT_DEFINE_FACE( 2, H ), nh );
        break;
        case 3:
            WRITE_VPIN( SELECT_DEFINE_FACE( 3, V ), nv );
            WRITE_VPIN( SELECT_DEFINE_FACE( 3, H ), nh );
        break;
        case 4:
            WRITE_VPIN( SELECT_DEFINE_FACE( 4, V ), nv );
            WRITE_VPIN( SELECT_DEFINE_FACE( 4, H ), nh );
        break;
        case 5:
            WRITE_VPIN( SELECT_DEFINE_FACE( 5, V ), nv );
            WRITE_VPIN( SELECT_DEFINE_FACE( 5, H ), nh );
        break;
        default:
        break;
    }
    
}
