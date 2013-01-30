package org.kornicameister.tutorial.qubic2;

import org.hibernate.Session;
import org.junit.Assert;
import org.junit.Test;
import org.kornicameister.tutorial.AbstractTest;
import org.soqqo.datagen.RandomDataGenerator;
import org.soqqo.datagen.config.DataTypes;
import org.soqqo.datagen.config.GenConfig;

import java.io.Serializable;
import java.util.List;

/**
 * @author kornicameister
 * @since 0.0.1
 */
public class UserWriteTest extends AbstractTest {

    @Test
    public void testAddUsers() {
        System.out.println("User :: Write :: test :: start");
        Session session = AbstractTest.HB.openSession();
        RandomDataGenerator rdg = new RandomDataGenerator();
        Serializable id;

        List<User> randomPersons = rdg.generateList(50,
                new GenConfig()
                        .name(DataTypes.Name.Firstname, "firstName")
                        .name(DataTypes.Name.Lastname, "lastName"), User.class);

        session.getTransaction().begin();
        for (User user : randomPersons) {
            id = session.save(user);
            Assert.assertNotNull("ID is null, therefore bad", id);
        }
        session.getTransaction().commit();

        session.close();
        System.out.println("User :: Write :: test :: ok");
    }
}
