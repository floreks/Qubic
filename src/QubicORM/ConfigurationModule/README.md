# ConfigurationModule
## Where it all starts

I believe that configuration module is the first one
on the tangled path to illumination of the Qubic.

It holds all classes and resources that can be summed up
by following points:
* data objects (which is objective version of the read cfg file)
* cfg reader (a class or group of classes that can read options located in the cfg file)

# IMPORTANT
ConfigurationModule will be likely using some validation tool againts
runtime checkup of the cfg files being or not valid. I believe that this
functionality should be placed in Utilities as it has some opportunity
for reusability.
