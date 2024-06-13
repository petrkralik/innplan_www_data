<?php


namespace page\WorkType;


class WorkTypeDelete extends WorkType
{


	const string ACTION_CONFIRMATION = "confirmation";

	const string ACTION_PROCESSING = "processing";


	/**
	 * @throws \page\Exception|\DOMException
	 */
	function getContentMain(): ?\iw\dom\Element
	{
		$dom= null;
		try {
			if ($this->detectProcess() == self::ACTION_PROCESSING) {
				$dom = $this->delete();
			} else {
				// Confirmation
				$this->getWorkTypeId();
				$dom = $this->domConfirmation();
			}
		}
		catch (\businessObject\Exception|\businessObject\property\Exception $ex) {
			\page\Error::GENERAL->throw("Došlo k chybě");
		}

		return $this->dom->div(\N, $dom);
	}


	/**
	 * @throws \businessObject\Exception
	 * @throws \businessObject\property\Exception
	 */
	private function delete(): bool
	{
		return $this->getBusinessObject()->delete();
	}



	private function detectProcess(): string
	{
		return match ($this->uriMatches[2] ?? null) {
			"processing" => self::ACTION_PROCESSING,
			default => self::ACTION_CONFIRMATION,
		};
	}


	/**
	 * @throws \DOMException
	 */
	private function domConfirmation(): array
	{
		return [
			$this->dom->p(\N, "Opravdu chcete tento ty práce smazat?"),
			$this->domButtonBack(),
			$this->domButtonConfirm(),
		];
	}


	/**
	 * @throws \DOMException
	 */
	private function domButtonBack(): \iw\dom\Element
	{
		return $this->dom->a(\N, \urlBasePage. "/workType/{$this->getWorkTypeId()}", "nemazat");
	}


	/**
	 * @throws \DOMException
	 */
	private function domButtonConfirm(): \iw\dom\Element
	{
		return $this->dom->a(\N, \urlBasePage. "/workType/{$this->getWorkTypeId()}/delete/processing", "ano, smazat");
	}


}