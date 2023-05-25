<?php

/** @generate-class-entries */
namespace Cassandra {
    /**
     * @strict-properties
     */
    final class Date implements Value {
        public function __construct(int $value = null) {}
        public function fromDateTime(\DateTimeInterface $datetime): Date {}
        public function toDateTime(): \DateTime {}
        public function seconds(): int {}
        public function type(): Cassandra\Type\Scalar {}

        public function __toString(): string {}
    }
}