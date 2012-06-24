
#include "FL/Entity/Component.h"

#include <iostream>

class TestComponent : public Component {

    public:
        static int times_processed;
        TestComponent() {

            _type = 1;
        
        }

        void Init() {};
        void Process() {
            std::cout << "Processed this TestComponent ";
            std::cout << ++times_processed;
            std::cout << " times!\n";
        };
        void Cleanup() {};
};

int TestComponent::times_processed = 0;

