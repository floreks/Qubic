package org.bridge;

/**
 * To be extended to re-implement {@link org.bridge.HibernateConfigurationDecorator#getHibernateCfgFile()}
 * method
 */
public abstract class HibernateConfigurationDecorator {
    public abstract String getHibernateCfgFile();
}
