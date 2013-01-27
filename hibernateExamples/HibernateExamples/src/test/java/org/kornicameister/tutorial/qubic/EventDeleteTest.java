package org.kornicameister.tutorial.qubic;

import org.hibernate.Session;
import org.junit.Assert;
import org.junit.Test;

import java.util.List;

/**
 * @author kornicameister
 * @since 0.0.1
 */
public class EventDeleteTest extends AbstractTest {

    @Test
    public void testDeleteEvent() {
        System.out.println("Delete :: test :: start");
        final Session session = AbstractTest.HB.openSession();
        final List list = session.createQuery("from Event").list();

        Assert.assertNotNull("List null, too bad, could ba empty, bot not null");

        for (Object e : list) {
            session.delete(e);
        }

        Assert.assertTrue("Elements could not have been removed",
                session.createQuery("from Event").list().size() != 0);

        session.close();

        System.out.println("Delete :: test :: ok");
    }

}
