#ifndef __FACE_H__
#define __FACE_H__

#include <inttypes.h>
#include "Configuration_lvm.h" 
#include "Color.h" 
#include "eps.h" 

class Face
{
public:
    Face();    
    
    void set_color( Color &c );
    void set_intensity( uint8_t nh, uint8_t nv);
    Color get_color();
    uint8_t get_h_intensity();
    uint8_t get_v_intensity();
    uint8_t get_detected();
    
    private:
    uint8_t id; // id auto-incr.
    uint8_t h; // Horizontale
    uint8_t v; // Verticale
    Color color; // Color
    
    static uint8_t current_id;
};
#endif // __FACE_H__
