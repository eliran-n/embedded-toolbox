#include <iostream>
#include <string>
#include <stdint.h>
#include <stdbool.h>

#define NAME_LEN 10

using namespace std;

class Sensor
{
    private:
    
        uint32_t id;
        char name[NAME_LEN];
        uint32_t value;
        bool is_active;

    public:

        Sensor(uint32_t id, const char* str_name): id(id), value(0), is_active(false)
        {
            strcpy(str_name, name, NAME_LEN);
        }

        void set_value(uint32_t new_value)
        {
            value = new_value;
        }

        uint32_t read_value()
        {
            return value;
        }

        void active_sensor()
        {
            is_active = true;
        }

        void disable_sensor()
        {
            is_active = false;
        }

        void print_sensor()
        {
            cout << "sensor status:" << endl;
            cout << "sensor id: " << id << endl;
            cout << "sensor name: " << name << endl;
            cout << "sensor value: " << value << endl;
            if ( is_active == true )
            {
                cout << "sensor is active." << endl;
            }
            else
            {
                cout << "sensor is disabled." << endl;
            }
        }

        void strcpy( const char* src_str, char* dest_str, uint32_t dest_len )
        {
            uint32_t i = 0;
            while(src_str[i] != '\0' && i<(dest_len-1))
            {
                dest_str[i] = src_str[i];
                i++;
            }
            dest_str[i] = '\0';
        }
};

int main()
{
    Sensor sensor(3, "Temperature");

    return 0;
}