
import events.inputevent as inputevent
from events.inputevent import InputEvent


def bindtest():
    print "test 1"
    i = InputManager()
    i.bind(bindtest2, inputevent.MOUSEBUTTONDOWN, 1)

def bindtest2():
    print "test 2"
    i = InputManager()
    i.bind(bindtest, inputevent.MOUSEBUTTONDOWN, 1)

class InputManager(object):
    _shared_state = {}

    # {inputKey: [[handled_this_frame, inputType], ...], ...}
    record = {}

    # {inputType: {inputKey: callback, ...}, ...}
    bound = {}
    def __init__(self):
        self.__dict__ = self._shared_state

        self.bind(bindtest, inputevent.MOUSEBUTTONDOWN, 1)

    def process(self, queue):
        self.update_frame()
        for e in queue:
            self.add(e)
        self._process()

    def add(self, e):
        if e.inputType == inputevent.NOEVENT:
            return

        if not self.record.has_key(e.inputKey):
            self.record[e.inputKey] = []

        events = self.record[e.inputKey]

        ## UPS
        if (e.inputType-1) & (e.inputType-2) == 0:
            ## Overwrite HOLDS
            try:
                if (events[-1][1]-2) & (events[-1][1]-3) == 0:
                    # Remove HOLD event
                    self.record[e.inputKey] = events[:-1]
            except IndexError:
                pass

        events.append([0, e.inputType])

    def update_frame(self):
        for inputKey in self.record.keys():
            events = self.record[inputKey]

            i = 0
            remove = []
            remove_all = False
            for e in events:
                e[0] = 0
                
                ## Remove leading NOEVENTS
                if e[1] == inputevent.NOEVENT:
                    if i == 0 and len(events) > 1:
                        remove.append(i)
                    i += 1
                    continue
                
                if e[1] == inputevent.MOUSEMOTION:
                    remove.append(i)
                    i += 1
                    continue

                ## Ignore Holds
                if (e[1]-2) & (e[1]-3) == 0:
                    i += 1
                    continue

                ## Change Ups to NOEVENTS
                if (e[1]-1) & (e[1]-2) == 0:
                    remove_all = True
                    break

                ## Change Downs to Holds
                if e[1] & (e[1]-1) == 0:
                    self.record[inputKey][i] = [0, e[1]+2]
                    i += 1
                    continue

                i += 1

            if remove_all:
                del self.record[inputKey]
                continue

            if remove == []:
                continue

            offset = 0
            for j in remove:
                del self.record[inputKey][j - offset]
                offset += 1

            if len(events) == 0:
                del self.record[inputKey]

    def _process(self):
        for inputKey in self.record.keys():

            for e in self.record[inputKey]:
                if e[0] == 1:
                    continue

                b = (e[1], inputKey)
                if self.bound.has_key(e[1]):
                    if self.bound[e[1]].has_key(inputKey):
                        self.bound[e[1]][inputKey]()
                        e[0] = 1

    def bind(self, callback, inputType, inputKey):
        if not self.bound.has_key(inputType):
            self.bound[inputType] = {}

        self.bound[inputType][inputKey] = callback

    def unbind(self, inputType, inputKey):
        try:
            del self.bound[inputType][inputKey]
            if len(self.bound[inputType]) == 0:
                del self.bound[inputType]
        except:
            pass

