
def process(comptype):
    def processdec(func):
        func.comptype = comptype
        return func
    return processdec

class Script(object):
    def __init__(self):
        self.scripts = {}
        for name, method in self.__class__.__dict__.iteritems():
            if hasattr(method, "comptype"):
                self.scripts[method.comptype] = method

    def process(self, comptype, entity):
        self.scripts[comptype](self, entity)

