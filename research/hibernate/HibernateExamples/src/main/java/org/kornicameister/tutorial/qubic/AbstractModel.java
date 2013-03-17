package org.kornicameister.tutorial.qubic;

import javax.persistence.*;
import java.io.Serializable;
import java.util.Date;

/**
 * Some abstract model that will be used to gather
 * metadata for all the tables.
 * Provided meta:
 * <ol>
 * <li>last - access timestamp</li>
 * <li>row version number</li>
 * </ol>
 *
 * @author kornicameister
 * @since 0.0.1
 */
@MappedSuperclass
public class AbstractModel implements Serializable {
    /**
     * When the class' field is declared with {@link javax.persistence.Temporal} annotation
     * and this field is initialized in each one of the class' constructors, than
     * one thing is more than sure. Hibernate will take care of updating this field.
     * This feature is quite useful if you would like to have a column
     * in database that will hold information about recent row's access.
     */
    @Temporal(TemporalType.TIMESTAMP)
    @Column(name = "lastAccess")
    protected Date modifiedAt;

    /**
     * {@link Version} is useful when you want to ensure
     * that optimistic-locking mechanism can be used.
     * <p/>
     * It is the most suitable when merging data.
     */
    @Version
    @Column(name = "version")
    private Integer version = 0;

    public AbstractModel() {
        super();
        this.modifiedAt = new Date();
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof AbstractModel)) return false;
        if (!super.equals(o)) return false;

        AbstractModel model = (AbstractModel) o;

        return !(modifiedAt != null ? !modifiedAt.equals(model.modifiedAt) :
                model.modifiedAt != null) && !(version != null ? !version.equals(model.version) :
                model.version != null);
    }

    @Override
    public int hashCode() {
        int result = super.hashCode();
        result = 31 * result + (modifiedAt != null ? modifiedAt.hashCode() : 0);
        result = 31 * result + (version != null ? version.hashCode() : 0);
        return result;
    }
}
