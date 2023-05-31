<?php

declare(strict_types=1);

namespace Cassandra\Tests\Unit\DateTime;

use Carbon\Carbon;
use Carbon\CarbonImmutable;
use Cassandra\Timestamp;
use Cassandra\Type;
use DateTime;
use DateTimeImmutable;
use DateTimeInterface;

it('creates new Cassandra\\Timestamp', function () {
    $timestamp = new Timestamp();

    expect($timestamp)->not->toBeNull();
});

it('Cassandra\\Timestamp::type', function () {
    $date = new Timestamp();

    expect($date->type())
        ->toBeInstanceOf(Type::class)
        ->not()
        ->toBeNull()
        ->and($date->type()->name())
        ->toBe('timestamp');
});

it('Cassandra\\Timestamp::microtime', function () {
    $date = new Timestamp();

    [$firstPart, $seconds] = explode(' ', microtime(false));

    $microtime = $date->microtime(true);

    expect($microtime)
        ->toBeFloat()
        ->and($date->microtime(false))
        ->toBe(number_format((int)((float)$firstPart * 1000) / 1000.0, 8) . ' ' . $seconds);
});

it('Cassandra\\Timestamp::time', function () {
    $date = new Timestamp();

    expect($date->time())
        ->toBe(time());
});


it('Create new Cassandra\\Timestamp from DateTime', function () {
    $date = Timestamp::fromDateTime(new DateTime());
    $date2 = Timestamp::fromDateTime(new DateTimeImmutable());
    $date3 = Timestamp::fromDateTime(Carbon::now());
    $date4 = Timestamp::fromDateTime(CarbonImmutable::now());

    expect($date)
        ->toBeInstanceOf(Timestamp::class)
        ->not()
        ->toBeNull()
        ->and($date2)
        ->toBeInstanceOf(Timestamp::class)
        ->not()
        ->toBeNull()
        ->and($date3)
        ->toBeInstanceOf(Timestamp::class)
        ->not()
        ->toBeNull()
        ->and($date4)
        ->toBeInstanceOf(Timestamp::class)
        ->not()
        ->toBeNull();
});

it('Cassandra\\Date::toDateTime', function () {
    $date = new Timestamp();

    expect($date->toDateTime())
        ->toBeInstanceOf(DateTimeInterface::class)
        ->not()
        ->toBeNull();
});


it('formats the string with __toString', function () {
    $date = new Timestamp();
    expect((string)$date)->toBe((string)(int)(microtime(true) * 1000));
});
