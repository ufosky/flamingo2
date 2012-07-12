
import flamingo

evtman = flamingo.ext.eventmanager.EventManager()
entman = flamingo.ext.entitymanager.EntityManager(evtman)

e = entman.CreateEntity()
c = flamingo.ext.component.Component(1)
e.AddComponent(c)

