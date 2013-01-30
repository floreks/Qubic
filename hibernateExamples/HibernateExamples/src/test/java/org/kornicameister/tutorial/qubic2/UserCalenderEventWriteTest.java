package org.kornicameister.tutorial.qubic2;

import org.hibernate.Session;
import org.junit.Test;
import org.kornicameister.tutorial.AbstractTest;
import org.kornicameister.tutorial.qubic.Event;
import org.soqqo.datagen.RandomDataGenerator;
import org.soqqo.datagen.RandomUtil;
import org.soqqo.datagen.config.DataTypes;
import org.soqqo.datagen.config.GenConfig;

import java.io.Serializable;
import java.util.*;

import static junit.framework.Assert.assertNotNull;
import static junit.framework.TestCase.assertTrue;

/**
 * @author kornicameister
 * @since 0.0.1
 */
public class UserCalenderEventWriteTest extends AbstractTest {
    private Session session;

    @Test
    public void testWriteCalendars() {
        session = AbstractTest.HB.openSession();

        final Set<User> users = this.getUsers();
        final List<Event> events = new ArrayList(this.getEvents());
        Serializable cId;

        assertTrue("Empty users list, error", users.size() != 0);
        assertTrue("Empty events list, error", events.size() != 0);

        session.beginTransaction();

        for (User u : users) {
            Calendar c = new Calendar(String.format("Calendar No [%s]", u.getLastName()), u);
            Set<Event> eventSet = new HashSet<>();
            for (int i = 0; i < new Random().nextInt(20); i++) {
                eventSet.add(RandomUtil.randomFromList(events));
            }
            c.setEvents(eventSet);
            cId = session.save(c);
            assertNotNull("Calendar ID is null, that is bad", cId);
        }

        session.getTransaction().commit();

        session.close();
    }

    public Set<User> getUsers() {
        Set<User> users;

        session.getTransaction().begin();
        {
            List usersList = session.createQuery("from User").list();
            if (usersList.size() > 0) {
                users = new HashSet<User>(usersList);
            } else {
                RandomDataGenerator rdg = new RandomDataGenerator();
                List<User> randomPersons = rdg.generateList(5,
                        new GenConfig()
                                .name(DataTypes.Name.Firstname, "firstName")
                                .name(DataTypes.Name.Lastname, "lastName"), User.class);
                for (User user : randomPersons) {
                    session.save(user);
                }
                users = new HashSet<>(randomPersons);
            }
        }
        session.getTransaction().commit();
        return users;
    }

    public Set<Event> getEvents() {
        Set<Event> events;

        session.getTransaction().begin();
        {
            List eventList = session.createQuery("from Event ").list();
            if (eventList.size() > 0) {
                events = new HashSet<Event>(eventList);
            } else {
                events = new HashSet<>();
                for (int i = 0; i < 20; i++) {
                    final Event event = new Event(String.format("Event No [%d]", new Random(i).nextInt()));
                    session.save(event);
                    events.add(event);
                }
            }
        }
        session.getTransaction().commit();
        return events;
    }
}
