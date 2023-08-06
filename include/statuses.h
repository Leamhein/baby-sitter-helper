#ifndef STATUSES_H
#define STATUSES_H

enum Statuses
{
    Disconnected,
    Active,
    Passive
};

class Statuses_Bus
{
    Statuses status;

public:
    Statuses_Bus(Statuses);
    void set_status(Statuses);
    Statuses get_status();
};

Statuses_Bus::Statuses_Bus(Statuses init_status)
{
    status = init_status;
}

void Statuses_Bus::set_status(Statuses new_status)
{
    status = new_status;
}

Statuses Statuses_Bus::get_status()
{
    return status;
}

extern Statuses_Bus status_bus(Disconnected);

#endif /* STATUSES_H */