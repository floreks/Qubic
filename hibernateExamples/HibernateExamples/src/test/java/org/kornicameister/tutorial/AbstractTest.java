package org.kornicameister.tutorial;

import org.hibernate.SessionFactory;
import org.junit.After;
import org.junit.Before;
import org.kornicameister.tutorial.access.HibernateBridge;

/**
 * @author kornicameister
 * @since 0.0.1
 */
public class AbstractTest {
    protected static SessionFactory HB;

    @Before
    public void setUp() throws Exception {
        HibernateBridge.accessHibernate();
        AbstractTest.HB = HibernateBridge.getSessionFactory();
    }

    @After
    public void tearDown() {
        HibernateBridge.closeHibernate();
    }
}
