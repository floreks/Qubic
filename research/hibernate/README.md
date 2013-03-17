This subdirectory can not be considered as the part of Qubic itself.

# Before you even start
Read [this](http://kornicameister.blogspot.com/2013/02/qubic-how-to-set-up-intellij-windows.html)
## Rules
* if you indent to create own examples I suggest to create own package under the **org** package
* the same rule is applied to the testing as well
* JUnit4 is the king

# HibernateExamples

HibernateExamples can be considered as the background review, research
of whatsoever that can be used for inspiration, understanding the
ways of how ORM should work and so on.

# Content

Each example in this directory must be collaborated along with the
validating tests, no other ones are permitted. Second requirment is
full documentation. These are examples, so the must answer as many
question as possible. 

# Maven
Examples are build and all the tests are run by Integrated maven.
Project includes only source code of the models and tests with
additional hibernate and maven configuration files (respectively
**hibernate.cfg.xml** and **pom.xml**). Please be cautios and not
include here IDE's spefic configuration files. AFAIK Maven, the project
based on it, requires no more than *pom.xml* to start working.

# Suggestion
1. read about ORM at all
2. checkout what is JPA
3. checkout Maven (only basics to run tests)

Useful links:
* [Hibernate 4.1 docs](http://docs.jboss.org/hibernate/orm/4.1/quickstart/en-US/html/)
* [Maven Mykong tutorial](http://www.mkyong.com/tutorials/maven-tutorials/)
* [Some models](https://www.dropbox.com/sh/vhshvs2j30xdeh8/z-tI54qOYt)
