#include "pb_encode.h"
#include "pb_decode.h"
#include "message.pb.h"
#include "Arduino.h"

int main() {
    Message original = Message_init_zero;
    Message decoded = Message_init_zero;
    uint8_t buffer[Message_size];
    pb_ostream_t ostream;
    pb_istream_t istream;
    
    original.kind = SensorKind::SensorKind_BMP280;
    strcpy(original.str, "coucou");

    ostream = pb_ostream_from_buffer(buffer, sizeof(buffer));
    if(!pb_encode(&ostream, &Message_msg, &original)) {
        // error
        Serial.println(ostream.errmsg);
    }

    istream = pb_istream_from_buffer(buffer, ostream.bytes_written);
    if(!pb_decode(&istream, &Message_msg, &decoded)) {
        Serial.println(istream.errmsg);
    }

    Serial.print("Destination message: ");
    Serial.println(decoded.str);
}
