
import flamingo

class TestScript(flamingo.script.Script):
    @flamingo.script.process(2)
    def screen(self, entity):
        print "TestScript!"


FLSCRIPT = TestScript

