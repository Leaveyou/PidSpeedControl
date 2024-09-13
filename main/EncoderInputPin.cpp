#include "arduino.h"
#include "Subscriber.h"
#include "Pin.h"
#include <vector>

template <int gpio_number> class EncoderInputPin: public Pin {
  public:

    inline static bool state = false;

    void attachTo(Subscriber *subscriber) override{
      this->subscribers.push_back(subscriber);
    }

    EncoderInputPin() {
      attachInterrupt(gpio_number, subroutine ,CHANGE);
    }

    static void subroutine() {
      updateState();
      notify(gpio_number);
    }

    int getPinNumber() override {
      return gpio_number;
    }

    bool getState() override {
      return state;
    }
    
    static void updateState() {
      state = (bool)digitalRead(gpio_number);
    }
  
  protected:
    inline static std::vector<Subscriber*> subscribers;

    static void notify(int pin_number) {
      for(int i = 0; i < subscribers.size(); i++) {    
          subscribers[i]->update(pin_number);
      }
    }
};
