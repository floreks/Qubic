package org.bridge;

import org.hibernate.SessionFactory;
import org.hibernate.cfg.Configuration;
import org.hibernate.service.ServiceRegistry;
import org.hibernate.service.ServiceRegistryBuilder;

public class HibernateBridge {
    private static SessionFactory sessionFactory = null;

    public static SessionFactory getSessionFactory() {
        return sessionFactory;
    }

    /**
     * Some useful static method that will create Hibernate connection
     * in the way you like. {@link HibernateConfigurationDecorator} is
     * an abstract class that has only one method that should return path
     * to your Hibernate cfg file.
     *
     * @param decorator
     * @return true if all good
     */
    public static boolean accessHibernate(HibernateConfigurationDecorator decorator) {
        Configuration configuration = new Configuration();
        configuration = configuration.configure(decorator.getHibernateCfgFile());

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
