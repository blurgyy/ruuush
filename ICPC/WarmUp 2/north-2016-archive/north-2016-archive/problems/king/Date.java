public class Date implements Comparable<Date> {
    final static int[] daysInMonth = {-1, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int day;
    int month;
    int year;

    public Date(int day, int month, int year) {
        this.day = day;
        this.month = month;
        this.year = year;
    }

    @Override
    public String toString() {
        return day + " " + month + " " + year;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;

        Date date = (Date) o;

        if (day != date.day) return false;
        if (month != date.month) return false;
        return year == date.year;

    }

    @Override
    public int hashCode() {
        int result = day;
        result = 31 * result + month;
        result = 31 * result + year;
        return result;
    }

    @Override
    public int compareTo(Date date) {
        if (year != date.year) return Integer.compare(year, date.year);
        if (month != date.month) return Integer.compare(month, date.month);
        return Integer.compare(day, date.day);
    }

    Date change(int x) {
        Date newDate = new Date(this.day + x, this.month, this.year);
        newDate.fix();
        return newDate;
    }

    void fix() {
        while (month >= 13) {
            month -= 12;
            year++;
        }

        while (month <= 0) {
            month += 12;
            year--;
        }

        while (day > daysInMonth[month]) {
            day -= daysInMonth[month];
            month++;
            if (month == 13) {
                year++;
                month = 1;
            }
        }

        while (day <= 0) {
            month--;
            if (month == 0) {
                year--;
                month = 12;
            }
            day += daysInMonth[month];
        }
    }
}
