package org.marmac;

import org.bridge.HibernateConfigurationDecorator;

public class MyHibernateAccess extends HibernateConfigurationDecorator
{
    @Override
    public String getHibernateCfgFile()
    {
        return "marmac/hibernate.cfg.xml";
    }
}
