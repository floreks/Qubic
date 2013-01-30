package org.kornicameister.tutorial.qubic2;

import org.kornicameister.tutorial.qubic.IDModel;

import javax.persistence.*;
import java.util.Set;

/**
 * <b>User</b>
 * <p>
 * It takes part in {@link OneToMany} association example.
 * One user may have more than one {@link Calendar} therefore this
 * kind of ownership must be described via 1:m relationship between
 * these objects.
 * <p/>
 * <p>
 * Another important thing in this class is that we have two fields:
 * <ul>
 * <li>{@link User#firstName}</li>
 * <li>{@link User#lastName}</li>
 * </ul>
 * that have no annotation assigned. This is not a bug and Hibernate knows
 * that these fields must be included in corresponding table (here <i>eventUser</i>).
 * <p>
 * One thing to remember. No annotation means that fields are described with default values.
 * Like for example, there is the {@link Basic} annotation used in the transparent way and
 * {@link Column} annotation is used like it would be written as follows:
 * <pre>
 *         \@Column(name = "firstName")
 *     </pre>
 * </p>
 *
 * @author kornicameister
 * @see User#calendarSet
 */
@Entity
@Table(name = "eventUser",
        uniqueConstraints = {@UniqueConstraint(columnNames = "lastName")})
public class User extends IDModel {
    private String firstName;
    private String lastName;

    /**
     * One last thing is {@link User#calendarSet} field that we use to point out that
     * exactly one user may have more than one calender. We achieve that by using an annotation
     * <ul>
     * <li>{@link OneToMany} - that describes relationship's direction</li>
     * </ul>
     * <p/>
     * You may notice that this field is also described with mappedBy attribute of the annotation.
     * That is the way to have {@link User} class with multiple calendars and at the same time
     * {@link Calendar} with singular {@link User} object reference.
     *
     * @see Calendar#user
     */
    @OneToMany(fetch = FetchType.LAZY, mappedBy = "user")
    private Set<Calendar> calendarSet;

    public User() {
        super();
    }

    public User(String firstName, String lastName) {
        this.firstName = firstName;
        this.lastName = lastName;
    }

    public String getFirstName() {
        return firstName;
    }

    public void setFirstName(String firstName) {
        this.firstName = firstName;
    }

    public String getLastName() {
        return lastName;
    }

    public void setLastName(String lastName) {
        this.lastName = lastName;
    }

    @Override
    public String toString() {
        final StringBuilder sb = new StringBuilder();
        sb.append("User");
        sb.append("{lastName='").append(lastName).append('\'');
        sb.append(", firstName='").append(firstName).append('\'');
        sb.append('}');
        return sb.append(" [ ").append(super.toString()).append(" ]").toString();
    }
}
