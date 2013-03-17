package org.kornicameister.tutorial.qubic;

import org.hibernate.Session;
import org.junit.Assert;
import org.junit.Test;
import org.kornicameister.tutorial.AbstractTest;

import java.io.Serializable;
import java.util.Random;

public class EventWriteTest extends AbstractTest {

    @Test
    public void testAddEvent() {
        System.out.println("Write :: test :: start");
        Session session = AbstractTest.HB.openSession();
        Serializable id;

        session.getTransaction().begin();
        for (int i = 0; i < 10; i++) {
            id = session.save(new Event(String.format("Event No [%d]", new Random(i).nextInt())));
            Assert.assertNotNull("ID is null, therefore bad", id);
        }
        session.getTransaction().commit();

        session.close();
        System.out.println("Write :: test :: ok");
    }

}
