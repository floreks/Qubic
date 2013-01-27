package org.kornicameister.tutorial.access;

import org.hibernate.SessionFactory;
import org.hibernate.cfg.Configuration;
import org.hibernate.service.ServiceRegistry;
import org.hibernate.service.ServiceRegistryBuilder;

public final class HibernateBridge {
    private static SessionFactory sessionFactory = null;

    public static SessionFactory getSessionFactory() {
        return sessionFactory;
    }

    public static boolean accessHibernate() {

        Configuration configuration = new Configuration();
        configuration = configuration.configure("/hibernate.cfg.xml");

        ServiceRegistry serviceRegistry = new ServiceRegistryBuilder()
                .applySettings(configuration.getProperties())
                .buildServiceRegistry();
        HibernateBridge.sessionFactory = configuration
                .buildSessionFactory(serviceRegistry);

        return !HibernateBridge.sessionFactory.isClosed();
    }

    public static boolean closeHibernate() {
        if (HibernateBridge.sessionFactory != null) {
            sessionFactory.close();
            return HibernateBridge.sessionFactory.isClosed();
        }
        return false;
    }

}
