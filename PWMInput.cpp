#include "Subscriber.h"
#include "Publisher.h"
#include "Pin.h"
#include "arduino.h"

class PWMInput: public Subscriber {
  public:
    PWMInput(Pin* pin) {
      this->pin = pin;
      this->pin->attachTo(this);
    }

    void update(int pin_number) {  
      bool state = this->pin->getState();
    }
  protected:
  private:
    Pin* pin;
};