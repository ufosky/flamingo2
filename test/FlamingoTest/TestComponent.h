
#include "FL/Entity/Component.h"

#include <iostream>

class TestComponent : public Component {

    public:
        static int times_processed;

        void Init() {};
        void Process() {
			std::cout << "Processed this TestComponent " << ++times_processed << " times!\n";
        };
        void Cleanup() {};

	protected:
		void _SetType() { _type = 100; };
};

int TestComponent::times_processed = 1;

