#include "lvm.h"


Face faces[LVM_FACES_NUM];

void lvm_set_face_intensity(uint8_t id, uint8_t h, uint8_t v)
{
    if ( id >= 0 && id < LVM_FACES_NUM )
    {
        faces[id].set_intensity( h,v );
    }
}

void lvm_set_global_intensity( uint8_t h, uint8_t v )
{
    for ( uint8_t i =0; i < LVM_FACES_NUM  ; ++i)
    {
        faces[i].set_intensity( h, v );
    }
}
uint8_t lvm_get_face_h_intensity(uint8_t id)
{
    if ( id >= 0 && id < LVM_FACES_NUM )
    {
        return faces[id].get_h_intensity();
    }
}

uint8_t lvm_get_face_v_intensity(uint8_t id)
{
    if ( id >= 0 && id < LVM_FACES_NUM )
    {
        return faces[id].get_v_intensity();
    }
}

void lvm_set_global_color(  Color &c )
{
    for ( uint8_t i =0; i < LVM_FACES_NUM  ; ++i)
    {
        faces[i].set_color( c );
    }
}

Color lvm_get_global_color()
{
    return faces[0].get_color();
}

uint8_t lvm_get_global_h_intensity()
{
    return faces[0].get_h_intensity();
}

uint8_t lvm_get_global_v_intensity()
{
    return faces[0].get_v_intensity();
}
