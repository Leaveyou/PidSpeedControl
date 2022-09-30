#include "Subscriber.h"
#include "Pin.h"

template <int gpio_number> class EncoderInputPin: public Pin {
  public:


    static boolean state;
    void attachTo(Subscriber *subscriber) override{
      
    }

    EncoderInputPin()
    {
      attachInterrupt(gpio_number, subroutine ,CHANGE);
    }
    static void subroutine() {
      updateState();
      notify(gpio_number);
    }

    int getPinNumber() override
    {
      return gpio_number;
    }

    bool getState() override
    {
      return state;
    }
    
    static void updateState() {
      state = (bool)digitalRead(gpio_number);
    }
  
  private:
  protected:
    static Subscriber *subscribers[3];
    static int existent_subscribers;

    static void notify(int pin_number) {
      for(int i = 0; i < existent_subscribers; i++) {    
          subscribers[i]->update(pin_number);
      }
    }

};

template<int gpio_number> boolean EncoderInputPin<gpio_number>::state = false;
template<int gpio_number> int EncoderInputPin<gpio_number>::existent_subscribers = 0;
template<int gpio_number> Subscriber *EncoderInputPin<gpio_number>::subscribers[3];

