<?php

declare(strict_types=1);

namespace Cassandra\Tests\Unit\DateTime;

use Carbon\CarbonImmutable;
use DateTime;
use Cassandra;
use Carbon\Carbon;
use Cassandra\Date;
use DateTimeImmutable;
use DateTimeInterface;

it('Create new Cassandra\\Date', function () {
    $date1 = new Date();
    $date2 = new Date(time());
    $date3 = new Date((string)time());

    expect($date1)
        ->toBeInstanceOf(Date::class)
        ->not()
        ->toBeNull()
        ->and($date2)
        ->toBeInstanceOf(Date::class)
        ->not()
        ->toBeNull()
        ->and($date3)
        ->toBeInstanceOf(Date::class)
        ->not()
        ->toBeNull();
});

it('Cassandra\\Date::toDateTime', function () {
    $date = new Date();

    expect($date->toDateTime())
        ->toBeInstanceOf(DateTimeInterface::class)
        ->not()
        ->toBeNull();
});


it('Cassandra\\Date::seconds', function () {
    $date = new Date();
    expect($date->seconds())
        ->toBe(Carbon::now()->startOfDay()->getTimestamp());
});


it('Create new Cassandra\\Date from DateTime', function () {
    $date = Date::fromDateTime(new DateTime());
    $date2 = Date::fromDateTime(new DateTimeImmutable());
    $date3 = Date::fromDateTime(Carbon::now());
    $date4 = Date::fromDateTime(CarbonImmutable::now());

    expect($date)
        ->toBeInstanceOf(Date::class)
        ->not()
        ->toBeNull()
        ->and($date2)
        ->toBeInstanceOf(Date::class)
        ->not()
        ->toBeNull()
        ->and($date3)
        ->toBeInstanceOf(Date::class)
        ->not()
        ->toBeNull()
        ->and($date4)
        ->toBeInstanceOf(Date::class)
        ->not()
        ->toBeNull();
});
