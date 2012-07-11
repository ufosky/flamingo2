
import flamingo

class TestScript(flamingo.script.Script):
    @flamingo.script.process(flamingo.ext.component.FL_COMPTYPE_SCREEN)
    def screen(self, entity):
        print "Script passed this entity: " + str(entity)


FLSCRIPT = TestScript

