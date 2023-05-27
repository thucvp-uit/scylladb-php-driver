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
use Cassandra\Exception\InvalidArgumentException;

it('throw exception on invalid string as number in __construct', function () {
    $date = new Date('hello world');
})->throws(InvalidArgumentException::class);
//
//it('Create new Cassandra\\Date', function () {
//    $date1 = new Date();
//    $date2 = new Date(time());
//    $date3 = new Date((string)time());
//
//    expect($date1)
//        ->toBeInstanceOf(Date::class)
//        ->not()
//        ->toBeNull()
//        ->and($date2)
//        ->toBeInstanceOf(Date::class)
//        ->not()
//        ->toBeNull()
//        ->and($date3)
//        ->toBeInstanceOf(Date::class)
//        ->not()
//        ->toBeNull();
//});
//
//it('Cassandra\\Date::toDateTime', function () {
//    $date = new Date();
//
//    expect($date->toDateTime())
//        ->toBeInstanceOf(DateTimeInterface::class)
//        ->not()
//        ->toBeNull()
//        ->and($date->toDateTime(new Cassandra\Time()))
//        ->toBeInstanceOf(DateTimeInterface::class)
//        ->not()
//        ->toBeNull();
//});
//
//
//it('Cassandra\\Date::type', function () {
//    $date = new Date();
//
//    expect($date->type())
//        ->toBeInstanceOf(Cassandra\Type::class)
//        ->not()
//        ->toBeNull()
//        ->and($date->type()->name())
//        ->toBe('date');
//});
//
//
//it('Cassandra\\Date::seconds', function () {
//    $date = new Date();
//    expect($date->seconds())
//        ->toBe(Carbon::now()->startOfDay()->getTimestamp());
//});
//
//
//it('Create new Cassandra\\Date from DateTime', function () {
//    $date = Date::fromDateTime(new DateTime());
//    $date2 = Date::fromDateTime(new DateTimeImmutable());
//    $date3 = Date::fromDateTime(Carbon::now());
//    $date4 = Date::fromDateTime(CarbonImmutable::now());
//
//    expect($date)
//        ->toBeInstanceOf(Date::class)
//        ->not()
//        ->toBeNull()
//        ->and($date2)
//        ->toBeInstanceOf(Date::class)
//        ->not()
//        ->toBeNull()
//        ->and($date3)
//        ->toBeInstanceOf(Date::class)
//        ->not()
//        ->toBeNull()
//        ->and($date4)
//        ->toBeInstanceOf(Date::class)
//        ->not()
//        ->toBeNull();
//});
//
//
//it('formats the string with __toString', function () {
//    $date = new Date();
//    expect((string)$date)->toBe(
//        'Cassandra\\Date(seconds=' . CarbonImmutable::now()->startOfDay()->getTimestamp() . ')'
//    );
//});