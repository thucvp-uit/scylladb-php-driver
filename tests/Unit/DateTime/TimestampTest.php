<?php

declare(strict_types=1);

namespace Cassandra\Tests\Unit\DateTime;

use Carbon\Carbon;
use Carbon\CarbonImmutable;
use Cassandra\Timestamp;
use DateTime;
use DateTimeImmutable;

it('Create new Cassandra\\Timestamp from DateTime', function () {
    $date = Timestamp::fromDateTime(new DateTime());
//    $date2 = Timestamp::fromDateTime(new DateTimeImmutable());
//    $date3 = Timestamp::fromDateTime(Carbon::now());
//    $date4 = Timestamp::fromDateTime(CarbonImmutable::now());

    expect($date)
        ->toBeInstanceOf(Timestamp::class)
        ->not()
        ->toBeNull()
//        ->and($date2)
//        ->toBeInstanceOf(Timestamp::class)
//        ->not()
//        ->toBeNull()
//        ->and($date3)
//        ->toBeInstanceOf(Timestamp::class)
//        ->not()
//        ->toBeNull()
//        ->and($date4)
//        ->toBeInstanceOf(Timestamp::class)
//        ->not()
//        ->toBeNull()
    ;
});

