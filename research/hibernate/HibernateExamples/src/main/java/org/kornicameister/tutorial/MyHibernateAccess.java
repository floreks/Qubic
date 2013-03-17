package org.kornicameister.tutorial;

import org.bridge.HibernateConfigurationDecorator;

public class MyHibernateAccess extends HibernateConfigurationDecorator {
    @Override
    public String getHibernateCfgFile() {
        return "kornicameister/hibernate.cfg.xml";
    }
}
