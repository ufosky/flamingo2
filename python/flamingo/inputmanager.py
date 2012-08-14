
import events.inputevent as inputevent
from events.inputevent import InputEvent

class InputManager(object):
    _shared_state = {}
    def __init__(self):
        self.__dict__ = self._shared_state

    def process(self, queue):
        for event in queue:
            if event.inputType == inputevent.MOUSEBUTTONDOWN:
                print event.inputKey

