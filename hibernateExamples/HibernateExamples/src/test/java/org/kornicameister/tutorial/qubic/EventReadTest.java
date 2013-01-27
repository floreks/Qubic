package org.kornicameister.tutorial.qubic;

import org.hibernate.Session;
import org.junit.Assert;
import org.junit.Test;

import java.util.List;

/**
 * @author kornicameister
 * @since 0.0.1
 */
public class EventReadTest extends AbstractTest {

    @Test
    public void testReadEvent() {
        System.out.println("Read :: test :: start");
        final Session session = AbstractTest.HB.openSession();
        final List list = session.createQuery("from Event").list();

        Assert.assertNotNull("List null, too bad, could ba empty, bot not null", list != null);
        System.out.println(String.format("Elements count = %d", list.size()));

        session.close();
        System.out.println("Read :: test :: ok");
    }
}
