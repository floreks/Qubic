package org.kornicameister.tutorial.qubic2;

import org.kornicameister.tutorial.qubic.Event;
import org.kornicameister.tutorial.qubic.IDModel;

import javax.persistence.*;
import java.util.Set;

/**
 * This class shows how models' associations works
 * with Hibernate.
 * <p/>
 * <h3>ManyToMany</h3>
 * <p style="font-style:italic">
 * Calendar holding information about the {@link org.kornicameister.tutorial.qubic.Event}'s.
 * Anw we follow this assumption that events may be assigned to multiple calendar
 * therefore shared between {@link User}s
 * <p>Check {@link Calendar#events}</p>
 * </p>
 *
 * @author kornicameister
 * @since 0.0.1
 */
@Entity
@Table(name = "calender")
public class Calendar extends IDModel {

    @Column(name = "calendarName",
            insertable = true,
            updatable = true,
            length = 40)
    private String name;

    /**
     * <b>ManyToMany</b> is well known and commonly used method to show
     * that there is a need to associate multiple object with the same number
     * of objects on the other side. For instance, here we have multiple events
     * assigned to multiple calendars.
     * <p/>
     * How to do it with Hibernate ?
     * All there is required is to use
     * <ul>
     * <li>
     * {@link ManyToMany} - that informs Hibernate about are desire to join calendars
     * and events in many to many like relationship
     * </li>
     * <li>
     * {@link JoinTable} - unlike in {@link OneToMany} association where
     * {@link JoinColumn} or {@link PrimaryKeyJoinColumn} are used, here we have
     * {@link JoinTable} which parameters are used to detect,describe the table
     * of m:m type. For example here we will get the table like this
     * <pre>
     * CREATE TABLE eventToCalender
     * (
     * event_id BIGINT NOT NULL,
     * calender_id BIGINT NOT NULL,
     * PRIMARY KEY ( event_id, calender_id ),
     * FOREIGN KEY ( event_id ) REFERENCES calender ( primaryKey ),
     * FOREIGN KEY ( calender_id ) REFERENCES event ( primaryKey )
     * );
     * </pre>
     * </li>
     * </ul>
     */
    @ManyToMany(fetch = FetchType.LAZY)
    @JoinTable(name = "eventToCalender",
            joinColumns = {@JoinColumn(name = "event_id", referencedColumnName = "primaryKey")},
            inverseJoinColumns = {@JoinColumn(name = "calender_id", referencedColumnName = "primaryKey")})
    private Set<Event> events;

    /**
     * <p>
     * Here we have the {@link ManyToOne} annotation usage. This annotation has one important
     * feature to remember. It described the field, not the collection of fields.
     * Required corresponding annotation is {@link JoinColumn} that describes against which column connection should be made.
     * <p/>
     * <p style="font-style:italic">
     * <b>{@link PrimaryKeyJoinColumn} - may be an alternative for {@link JoinColumn} if we are sure that
     * tables are joined by primary keys (described by {@link Id}</b>
     * </p>
     * <p/>
     * As a result of that we would get the table with following SQL:
     * <pre>
     * CREATE TABLE calender
     * (
     * primaryKey BIGINT PRIMARY KEY NOT NULL AUTO_INCREMENT,
     * lastAccess DATETIME,
     * version INT,
     * calendarName VARCHAR(40),
     * user_id BIGINT,
     * FOREIGN KEY ( user_id ) REFERENCES eventUser ( primaryKey )
     * );
     * CREATE UNIQUE INDEX hash ON calender ( hash );
     *
     * </pre>
     */
    @ManyToOne(optional = false)
    @JoinColumn(name = "user_id", referencedColumnName = "primaryKey")
    private User user;

    public Calendar() {
        super();
    }

    public Calendar(String name, User user) {
        this.name = name;
        this.user = user;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public Set<Event> getEvents() {
        return events;
    }

    public void setEvents(Set<Event> events) {
        this.events = events;
    }

    @Override
    public String toString() {
        final StringBuilder sb = new StringBuilder();
        sb.append("Calendar");
        sb.append("{name='").append(name).append('\'');
        sb.append(", events=").append(events);
        sb.append('}');
        return sb.append(" [ ").append(super.toString()).append(" ]").toString();
    }


}
