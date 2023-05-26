<?php

/**
* @generate-class-entries
*/
namespace Cassandra {
    /**
     * @strict-properties
     */
    final class Date implements Value {
        public function __construct(int|string $value = UNKNOWN) {}

        public static function fromDateTime(\DateTimeInterface $datetime): Date {}
        public function toDateTime(Time $time = UNKNOWN): \DateTime {}
        public function seconds(): int {}
        public function type(): Type\Scalar {}

        public function __toString(): string {}
    }
}