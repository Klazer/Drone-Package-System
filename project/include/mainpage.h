/*! \mainpage CSCI 3081 Delivery Simulation project
*================================================================================= 
* 
* Iteration 1 Documentation
* ================================================================================
* ********************************************************************************
* In this current iteration of the drone delivery system, one drone delivers one 
* package to one customer. The system relies on a heavy and complex code base 
* that is given as a façade, since we are using the façade pattern. As such I 
* cannot speak on much about what that all does but I can say something about 
* what I specifically wrote for the rest. In the UML diagram below we can see the 
* façade up at the top in the box offering interfaces and other things in the 
* background That I wouldn’t want to mess with anyway. Down below are some classes
* that use this façade and some others that assist in the implementation of the 
* different classes needed for the simulation.

<img src="../CSCI3081_IT1_UML.png" alt="letters" width="800" height="400">
********************************************************************************
* For more specific details of each class, navigate to their respective pages on 
* this generated doxygen page. For a summary of those same classes, read on! First
* and foremost for the drone delivery we have Entities. These are given an 
* interface through IEntity called EntityBase. This is where each entity are given
* a unique ID in order to be kept track of in the system through its constructor.

* Then using this EntityBase class are the Customer, Package, and Drone classes. 
* The customer doesn’t do much other than offer its location and give the 
* simulation what it needs to display them. Then the package also does much the 
* same, but since it Is being sent it has a delivery location as well. The Drone 
* does most of the work, The drone is given the packages position then it is given
* the customers position, and through the DeliverySimulation class it is also 
* given a pathway to follow to go to the package and deliver it. The package is
* moved only through the drone with this same function, which makes sense since a
* package cannot move itself. Through the UpdateEntity function inherited from 
* EntityBase the drone is moved along the given paths it received from 
* DeliverySimulation, picks up the package then delivers it through a second given
* path from DeliverySimulation, the other entities do not make use of this.

* The drone also contains a battery class to simulate a power supply, though in 
* this implementation of this iteration it merely exists.

* The Drone uses a VectorMaths object which contains functions that allow vector 
* addition, scalar multiplication and other necessary functions for moving the 
* drone in 3D space. Only The VectorMaths object is an interface for Vector3d and 
* Vector2d, though only 3d is used in this iteration, the 2d one is still there 
* for the future. 

* In the DeliverySimulation class, a collection of entities is made with the use
* of a factory, (see more on that later), and deliveries are scheduled, where the
* necessary information is passed into the drone to in order to make its delivery.
* This includes changing  states of the drone and the paths to traverse. The paths
* are generated using an IGraph object set with the umn scene and GetPath which is
* incredibly useful and something I had nothing to do with. Then an update
* function is called multiple times for some step of time each time, and the
* simulation progresses through the entities getting their positions and states
* altered based on the parameters that they’re given and check, until the package 
* is delivered to the customer. The RunScript function which is also important, is
* another item I had nothing to do with, and for good reason, left alone.

* Finally are the factories. Factories are used in this situation to create the 
* entities used in the simulation. Though how to go about that we had a few
* choices. First we could have used a Concrete factory pattern. As seen in the UML 
* diagram below, this would involve creating a factory class that would handle the
* creation of objects. Which is good for the client class that now it does much
* less, but leaves a problem. This sort of factory is not easily extendable, 
* and when it is extended, large amounts of code need to be refactored in the
* decision-making structure for creating the right object. A headache for anyone 
* given the task to do so. So this is good for its simplicity and ease of
* understanding and implementation, but bad, since it abandons SOLID principles 
* and is not easily extended and not closed for modification.

<img src="../concreteuml.png" alt="concrete" width="800" height="300">
********************************************************************************
* The Second factory we could have used is an Abstract factory pattern. As seen 
* in the UML below. This involves the creation of separate factories for each 
* type of object. This is easier to extend (good) since no code needs to be 
* changed in any of the established factories to add a new one. But we will 
* still need to refactor code within the main event class in order to decide
* which type of object to create, and thus leaves code open to modification (bad).

<img src="../abstractuml.png" alt="abstract" width="800" height="400">
********************************************************************************
* The third which is the one used in this iteration of the project, is the 
* Composite Abstract Factory pattern. Here as seen in the UML below, We have a
* IEntityFactory interface that the following all inherit a CreateEntity 
* function from. Currently there are three factories that are responsible for 
* the creation of IEntity objects a Drone, Customer or Package. And a composite
* factory that has methods to add these factories into a collection (vector) and
* its CreateEntity function, takes input and iterates over the collection of 
* factories to create an object using this input, and the output is the desired
* IEntity object. Which means if we needed to extend it all we need to do is add
* the new factory to the collection when the composite is being used in a 
* client, no other code needs to be changed in any factories or in the decision
* structure to create an entity. This method is good since it better enforces 
* SOLID principles by being extendable and closed off for modification, but bad
* since it is not easily understandable with its complexity, and it still needs
* an outside class to add the factories to the collection.

<img src="../compositeuml.png" alt="composite" width="800" height="400">
********************************************************************************

--------------------------------------------------------------------------------

Iteration 2 Documentation
================================================================================

--------------------------------------------------------------------------------
<img src="../CSCI3081_Group10_IT2_UML.png" alt="letters" width="800" height="400">
## Designing and Implementing the Routes
In the first iteration of this project, a drone had only one route option: the 
smart route. This route allowed the drone to plot a path that followed city
streets to its destination. Although a perfectly acceptable way to get from
point A to point B, implementing only this route ignored the main advantage of
drone-implemented package delivery: namely, that the drone can fly. With this
in mind, in the second iteration we added two more route options for the drone 
that took advantage of this capability. The parabolic route allows the drone to 
travel in a parabolic shape from the origin to the destination, and the beeline
route provides a straight-line path.

As each of these paths achieves the same goal through different methods, we 
found the strategy pattern to be the most appropriate option for implementing
these behaviors. We created an interface containing a method called _doPath()_, 
which, when called, would produce a path for the drone to follow. We then 
created a number of concrete classes, one of each for the smart, parabolic, and 
beeline routes. These classes inherited from the interface spoken of above, and
each overrode the _doPath()_ method to produce their respective routes. Finally,
we added a new member variable to the drone class. This member variable is a 
pointer to an object of the same type as the interface class; as it is impossible 
to instantiate a pure virtual object, the drone constructor assigns the pointer
to a new instance of one of the three child classes instead. When a route is 
needed, the program simply has to call the _doPath()_ function from that object 
pointer, with no need to know what type of path it would be receiving.

Using the strategy pattern in this way allowed us to encapsulate the delivery 
behavior of the drone. It made the behavior open to extension by creating more 
concrete route classes as children of the interface, but kept it closed to 
modification in that there is no need to disrupt existing code to add these 
additional routes. It also makes use of runtime binding, allowing the delivery 
behavior of the drone to be determined when _doPath()_ is called and making 
lengthy and repetitive if and switch statements unnecessary. Of course, 
implementing a complex pattern like this for the first time wasn't easy; our 
team made a lot of use of the lecture slides and readings on Canvas to clarify 
points of confusion, and we found the parabolic path solution document 
particularly helpful in developing that concrete class. The strategy pattern 
made it easy to implement the drone's delivery behavior in interation 2 using 
good object-oriented design principles.

## Teamwork Documentation
Development Lead: Sebastian
Scheduler: Michael
Reporter: Isaiah
Project Manager: Anya

Iteration 2 Meeting 1 3/31/2021
Anya and Isaiah were assigned with implementing the strategy pattern, Michael
was assigned with modifying the batteries so they drain and affect the simulation
when they die, and Sebastian was assigned with getting the simulation to reschedule
packages whose deliverer entities died in the middle of its delivery. All of us
looked over and approved our changes via the GitHub pull requests.

Iteration 2 Meeting 2 4/13/2021
Anya and Isaiah discussed the general layout of where to implement the strategy
pattern and how to implement the parabolic path. Michael and Sebastian discussed
the specifics for how the battery should work. All of us looked over and approved
our changes via the GitHub pull requests.

Iteration 2 Meeting 3 4/18/2021
Final touches.
We all checked that the new functions that we individually added for this deliverable
were properly documented. Anya wrote the route discussion for the mainpage. Sebastian
wrote this Teamwork Documentation. Isaiah and Michael updated the Google Tests to
accommodate the changes made for this deliverable. All of us discussed the changes
we are making (specifically about the mainpage content and the route strategy tests)
and looked over and approved our changes via the GitHub pull requests.

## Observer Pattern Design Discussion
Please note that the observer pattern implementation for our simulation works. Also,
the observer pattern tests are in the test files of the subjects, which are the drone,
robot, and package test files.

Since the observers are given, we focused on creating the subject functionality of
the observer pattern for the simulation. Since the subjects in our simulation are the
entity classes, the subject functionality was given to the EntityBase class.
EntityBase was given a vector of observers so each subject can notify its observers
with its Notify() function. The DeliverySimulation class sets the observers of the
entities as they are scheduled in the simulation using the SetObservers() function in
EntityBase. This way, the subjects do not have to be dependent on the
DeliverySImulation class for the list of observers for each Notify() call, which
keeps coupling low.

The EntityBase class has a virtual function called createEvent() which helps create
picojson values of picojson objects based on a string that is passed in. For example,
passing in “en route” creates the picojson value that needs to be passed into Notify()
to send a notification of a package that is currently en route to its destination.
The createEvent() function is meant to make Notify() calls more concise, but it also
allows each entity class that derives from EntityBase to only have the picojson values
that they are responsible for. This is open for extension since new entities can have
their own notification types independent of the other entities. It is also closed to
modification because the other entities do not have to be changed when adding a new
entity due to how their observer functionality is independent of each other.

The observer pattern results in subjects that function independent of the main program
and of each other. The observer pattern allows us to reduce coupling with
DeliverySimulation by having subjects keep track of their own observers. The observer
pattern also allows for extension, while being closed to modification, by having each
subject derive from EntityBase to have their own notification types independent of
the other entity classes.

--------------------------------------------------------------------------------

Iteration 3 Documentation
================================================================================
--------------------------------------------------------------------------------
<img src="../CSCI3081_Group10_IT3_UML.png" alt="letters" width="800" height="400">
## Iteration 3: Drone/Robot Functionality
We have chosen for iteration 3 to implement more realistic additional 
functionality to the drone/robot delivery system by allowing the drones
and robots to carry more than a single package and not allowing a 
drone/robot to exceed its max speed.

The Drones and robots now inherit off of a Deliverer abstract class which
inherits off of Entity_Base to significantly reduce the amount of 
redundant code from previous iterations. Drones/Robots may be referred
as deliverers from now on.

Since Iteration 2 a deliverer will not exceed its maximum speed, since 
the speed it is given is the max speed. Each created deliverer receives 
this value in the picojson object used to initialize them.

To carry multiple packages some changes to the deliverers needed to be
made. Each package has its own weight. Each drone/robot has their
own maximum carrying capacity. Finally each deliverer now also holds 
collections of packages, and collections of paths between packages and 
paths between customers.

When the deliveries are scheduled, A drone or robot is checked to see if 
it is capable of taking the package, that is if it will not exceed its 
carrying capacity if it takes on another package. If it will be exceeded, 
the next deliverer is checked to see if it may take on another package. If 
no delivers can take it, the package is placed onto a backlog to be scheduled 
later as in the previous iteration. The main difference with this iteration 
is that, if the carrying capacity is not exceeded, the package is added onto 
a vector of packages. Then the path from the previous package to this package 
is added to the deliverers vector of initial travel paths. Another path from 
the previous packages destination to this current packages destination is 
added on to the deliverers vector of delivery paths. Then the first travel 
path added is altered to be a path from that package to the first customer in 
the delivery paths. 

The result of packages being scheduled this way is that the deliverer, 
will travel to all of the packages that it has been scheduled to 
deliver and pick them all up. Then once fully loaded and the last package 
is collected, the deliverer follows a path transitioning from travel paths 
to delivery paths. Then it uses this collection of delivery paths in order to 
deliver each package to each customer one after the other in succession. 
In this way a deliverer may deliver multiple packages at once. And since 
the code has been altered to run on these new vectors of packages and 
customers, it still retains the functionality of the previous iteration.

The biggest difficulty was working with old code that was written for 
single package deliveries. Large amounts of code needed to be refactored 
to operate with many new vectors of different objects, avoiding infinite 
loops and accidentally losing information with packages as they were moved 
around and operated on. For example, ScheduleDelivery() needed to be able to 
work with a deliverer's previously scheduled route and packages to add a new 
addition to the route so that the new package can be picked up and delivered
by the deliverer. Another example is that care needed to be made to keep
track of all the packages that still needed to be scheduled when iterating 
over them to find one that had a low enough weight to be scheduled to an 
available deliverer. A temporaty stack was used instead of iterating over a 
vector since elements might be removed from it, so a two stack approach is 
used. 


## Iteration 3 Team Documentation
Iteration 3 Meeting 1, 4/21/2021 
We discussed the feature we would like to implement, and decided on the 
Drone/Robot Functionality feature. Isaiah and Sebastian were assigned to
implement the feature, and Anya and Michael were assigned the testing 
and documentation.

Iteration 3 Meeting 2, 4/26/2021
Isaiah and Sebastian updated Anya and Michael with where they were in the
implementation, and the group decided that it was appropriate to begin
writing tests and starting documentation. Anya started work on the Robot
class tests, and Michael started work on the Drone class tests.

Iteration 3 Meeting 3, TBD

--------------------------------------------------------------------------------

Simulation Instructions
================================================================================

--------------------------------------------------------------------------------

* ## obtain the code
First, ensure that you are in the folder you would like to store the repo in. 
Then run the following command:

```
git clone https://github.umn.edu/umn-csci-3081-s21/repo-iter3-01-10.git
```

* ## compile the code
* Navigate to the project directory in the cloned repo, and then run the
* following command to compile the project:
 
 ```
 make
 ```

* this will use the makefile and compile the files into an executable

* ## execute the simulation
* To run that executable from the project folder, run
*
* ```
* ./bin/run.sh 
* ```
*
* Make sure you are in the /project directory, or the simulation will not run!
*
* If you see a permission error when trying to run the simulation, run the command
* below:
*
* ```
* chmod +x ./bin/run.sh
* ```
* and try running the above command again.
*
* Then to start and see the simulation, open a browser 
* and go to http://127.0.0.1:8081/
* Once the simulation opens, click on the drop down menu on the right side 
* and select an entity to center the view on that entity and get the best angle 
* on the simulation. Use ctrl click and drag to pan and the scroll wheel 
* to zoom in and out to change your view if/when needed. 

* Once the package is delivered remember to kill the simulation
* with with "kill simulation" button.

## Instructions for running the new Iteration 3 scene files
Complete the instructions above, stopping at the section titled "execute the simulation".
Ensure that you are in the /project directory, then run one of the following commands:

```
./bin/run.sh scenes/drone_and_robot_carry_capacity.json
```
_Run the above to see a demonstration of the robot and drone entities delivering multiple
packages with the addition of a weight limit._

```
./bin/run.sh scenes/drone_and_robot_carry_capacity_low_battery.json
```
_Run the above to see a demonstration of the robot and drone entities delivering multiple
packages with the addition of a weight limit and with battery limitations._

If you see a permission error when trying to run the simulation, run the command
below:

```
chmod +x ./bin/run.sh
```
and try running one of the above commands again.

Then to start and see the simulation, open a browser
and go to http://127.0.0.1:8081/
Once the simulation opens click on the drop down menu on the right side
and select either drone or robot to center the view on your chosen
entity and get the best angle on the simulation. 
Use ctrl click and drag to pan and the scroll wheel
to zoom in and out to change your view if/when needed.
You will then see your chosen entity moving along its path towards the packages
to deliver to the customer.

Once the package is delivered remember to kill the simulation
with with "kill simulation" button.














*/
