package org.kornicameister.tutorial.qubic;

import org.hibernate.annotations.NaturalId;

import javax.persistence.*;
import java.util.Date;

@Entity
@Table(name = "event")
public class Event extends PersistenceObject {
    @Column(name = "title", insertable = true, nullable = false, updatable = true)
    private String title;

    @Temporal(TemporalType.TIMESTAMP)
    @Column(name = "lastAccess")
    private Date date;


    public Event() {
        super();
        this.date = new Date();
    }

    public Event(String title) {
        this.title = title;
        this.date = new Date();
    }

    public Date getDate() {
        return date;
    }

    public void setDate(Date date) {
        this.date = date;
    }

    public String getTitle() {
        return title;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof Event)) return false;
        if (!super.equals(o)) return false;

        Event event = (Event) o;

        if (date != null ? !date.equals(event.date) : event.date != null) return false;
        if (title != null ? !title.equals(event.title) : event.title != null) return false;

        return true;
    }

    @Override
    public int hashCode() {
        int result = super.hashCode();
        result = 31 * result + (title != null ? title.hashCode() : 0);
        result = 31 * result + (date != null ? date.hashCode() : 0);
        return result;
    }

    @Override
    public String toString() {
        final StringBuilder sb = new StringBuilder();
        sb.append("Event");
        sb.append("{title='").append(title).append('\'');
        sb.append(", date=").append(date);
        sb.append('}');
        return sb.append(" [ ").append(super.toString()).append(" ]").toString();
    }
}
