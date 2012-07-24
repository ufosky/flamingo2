
import flamingo

class TestScript(flamingo.script.Script):
    @flamingo.script.process(flamingo.component.FL_COMPTYPE_SCREEN)
    def screen(self, entity):
        #print "Script passed this entity: " + str(entity)
        #print entity.GetAs(2)
        pass


FLSCRIPT = TestScript

