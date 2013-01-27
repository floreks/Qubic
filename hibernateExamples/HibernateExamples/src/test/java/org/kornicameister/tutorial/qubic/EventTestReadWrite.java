package org.kornicameister.tutorial.qubic;

import org.hibernate.Session;
import org.hibernate.SessionFactory;
import org.junit.After;
import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;
import org.kornicameister.tutorial.access.HibernateBridge;

import java.io.Serializable;
import java.util.Random;

public class EventTestReadWrite {
    private static SessionFactory HB;

    @Before
    public void setUp() throws Exception {
        System.out.println("Starting...");
        if (HibernateBridge.accessHibernate()) {
            System.out.println("Hibernate accessed");
        }
        EventTestReadWrite.HB = HibernateBridge.getSessionFactory();
        if (EventTestReadWrite.HB != null) {
            System.out.println("Hibernate is up and running");
        }
    }

    @After
    public void tearDown() {
        if (HibernateBridge.closeHibernate()) {
            System.out.println("Hibernate is down");
        }
    }

    @Test
    public void testReadEvent() {
        Session session = EventTestReadWrite.HB.openSession();

        for (Object e : session.createQuery("from Event").list()) {
            System.out.println(e);
        }

        session.close();
    }

    @Test
    public void testAddEvent() {
        Session session = EventTestReadWrite.HB.openSession();
        Serializable id;

        session.getTransaction().begin();
        for (int i = 0; i < 100; i++) {
            id = session.save(new Event(String.format("Event No [%d]", new Random(i).nextInt())));
            Assert.assertNotNull("ID is null, therefore bad", id);
        }
        session.getTransaction().commit();

        session.close();
    }


}
