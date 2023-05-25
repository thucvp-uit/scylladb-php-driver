<?php

/**
* @generate-class-entries
*/
namespace Cassandra {
    /**
     * @strict-properties
     */
    final class Date implements Value {
        public function __construct(int $value = null) {}

        public static function fromDateTime(\DateTimeInterface $datetime): Date {}
        public function toDateTime(?Time $time = null): \DateTime {}
        public function seconds(): int {}
        public function type(): Type\Scalar {}

        public function __toString(): string {}
    }
}